(function ($) {
  Drupal.behaviors.ws_tb ={
    scriptadded: false,

    attach: function(context, settings) {
      if (this.scriptadded) {
        twttr.widgets.load();
      } else {
        $('a.service-links-twitter-widget', context).each(function(){
          $(this).attr('href', $(this).attr('href').replace(/((?:counturl\=|^))http[s]*\%3A\/\//g, "$1"));
        });
        $.getScript('http://platform.twitter.com/widgets.js', function () {
          this.scriptadded = true;
        });
      }
    }
  }
})(jQuery);
;
(function ($) {
  Drupal.behaviors.ws_fl = {
    attach: function (context, settings) {
      $('a.service-links-facebook-like', context).each(function(){
        var iframe = document.createElement('iframe');

        iframe.src = $(this).attr('href').replace('http://', '//').replace(/http[s]*\%3A\/\//, '');
        iframe.setAttribute('scrolling', 'no');
        iframe.setAttribute('frameborder', 0);
        iframe.setAttribute('allowTransparency', 'true');

        $(iframe).css({
          'border': 'none',
          'overflow': 'hidden',
          'width': Drupal.settings.ws_fl.width + 'px',
          'height': Drupal.settings.ws_fl.height + 'px',
        });
       
        $(iframe).addClass($(this).attr('class'));

        $(this).replaceWith(iframe);
      });
    }
  }
})(jQuery);
;
(function ($) {
   Drupal.behaviors.ws_gpo = {
    scriptadded: false,

    attach: function (context, settings) {
      $('a.service-links-google-plus-one', context).once(function(){
        var g_text = document.createElement('g:plusone');

        g_text.setAttribute('href', $(this).attr('href'));
        g_text.setAttribute('width', Drupal.settings.ws_gpo.width);

        if (Drupal.settings.ws_gpo.size != '') {
          g_text.setAttribute('size', Drupal.settings.ws_gpo.size);
        }
        if (Drupal.settings.ws_gpo.annotation != '') {
          g_text.setAttribute('annotation', Drupal.settings.ws_gpo.annotation);
        }
        if (Drupal.settings.ws_gpo.callback) {
          g_text.setAttribute('callback', Drupal.settings.ws_gpo.callback);
        }

        $(this).replaceWith(g_text);
      });

      if (this.scriptadded) {
        gapi.plusone.go();
      } else {
        var params = { parsetags: "explicit" };

        if (Drupal.settings.ws_gpo.lang != '') {
          params.lang = Drupal.settings.ws_gpo.lang;
        }

        window.___gcfg = params

        $.ajax({
          url: "https://apis.google.com/js/plusone.js",
          dataType: "script",
          cache: true,
          success: function () {
            this.scriptadded = true;
            gapi.plusone.go();
          }
        });
      }
    }  
  }
})(jQuery);
;
