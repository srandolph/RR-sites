(function($) {
  Drupal.behaviors.realestateSimpleGMap = {
    attach: function (context, settings) {

      var options = {
        zoom: Drupal.settings.simplegmap.zoom,
        zoomControl: true,
        zoomControlOptions: {
          style: google.maps.ZoomControlStyle.LARGE,
          position: google.maps.ControlPosition.LEFT_CENTER
        },
        mapTypeId: google.maps.MapTypeId[Drupal.settings.simplegmap.maptype]
      }

      var map = new google.maps.Map(document.getElementById('map_canvas'), options);

      var geocoder = new google.maps.Geocoder();

      geocoder.geocode({'address': Drupal.settings.simplegmap.address}, function (results, status) {
        if (status == google.maps.GeocoderStatus.OK) {
          map.setCenter(results[0].geometry.location);
          var marker = new google.maps.Marker({
            map: map,
            position: results[0].geometry.location
          });
        }
      });

    }
  }
})(jQuery);
