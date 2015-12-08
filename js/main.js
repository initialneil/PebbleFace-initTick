(function() {
  loadOptions();
  submitHandler();
})();

$('.color-scheme').on('click', function() {
  scheme = $(this).data('info');
  scheme = scheme.split(',');
  $(scheme).each(function(index, key) {
    if (index % 2 == 0) {
      var value = scheme[index+1];
      if (value) {
        key = key.replace(/_/g, '-');
        value = value.replace('0x', '#');
        $('input[name=' + key).val(value);
        $('input[name=' + key).parent().children('.item-styled-color').children('.value').css('background', value);
        //console.log(index, key, value);
      }
    }
  });
  alert('apply color scheme!');
});

function submitHandler() {
  var $submitButton = $('#submitButton');

  $submitButton.on('click', function() {
    console.log('Submit');

    var return_to = getQueryParam('return_to', 'pebblejs://close#');
    document.location = return_to + encodeURIComponent(JSON.stringify(getAndStoreConfigData()));
  });
}

function loadOptions() {
  var $default_location = $('input[name=default-location]');

  if (localStorage.getItem("location_opt")) {
    $default_location.val(localStorage.default_location);
    var $location_opt = $('select[name=location-opt]');
    
    var location_opt_val = localStorage.location_opt;
    $location_opt.children().each(function() {
      var $opt = $(this);
      if ($opt.val() === location_opt_val) {
        $opt.prop('selected', true);
      }
    });
  }

  // process toggle
  $('input.item-toggle').each(function() {
    var name = $(this).attr('name');
    var key = name.replace(/\-/g, '_');
    if (localStorage.getItem(key)) {
      $(this)[0].checked = localStorage[key] == 'true';
    }
  });

  // change temperature format
  if ($('input[name=weather-celsius]')[0].checked == true)
    $('#weather-format').text('Celsius');
  else
    $('#weather-format').text('Fahrenheit');
  
  // process colors
  $('input.item-color').each(function() {
    var name = $(this).attr('name');
    var key = name.replace(/\-/g, '_');
    if (localStorage.getItem(key))
      $(this).val(localStorage[key]);
  });
}

$('input[name=weather-celsius]').on('click', function() {
  // change temperature format
  if ($(this)[0].checked == true)
    $('#weather-format').text('Celsius');
  else
    $('#weather-format').text('Fahrenheit');
});

function getAndStoreConfigData() {
  var $default_location = $('input[name=default-location]');
  var $location_opt = $('select[name=location-opt]');

  var options = {
    default_location: $default_location.val(),
    location_opt: $location_opt.val(),
  };

  localStorage.default_location = options.default_location;
  localStorage.location_opt = options.location_opt;

  // process toggle
  $('input.item-toggle').each(function() {
    var name = $(this).attr('name');
    var key = name.replace(/\-/g, '_');
    options[key] = $(this)[0].checked;
    localStorage[key] = $(this)[0].checked;
  });
  
  // process colors
  var color_scheme = "";
  $('input.item-color').each(function() {
    var name = $(this).attr('name');
    var val = $(this).val();
    var key = name.replace(/\-/g, '_');
    color_scheme += key + "," + val + ",";
    localStorage[key] = val;
  });
  options.color_scheme = (color_scheme);

  console.log('Got options: ' + JSON.stringify(options));
  return options;
}

function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}
