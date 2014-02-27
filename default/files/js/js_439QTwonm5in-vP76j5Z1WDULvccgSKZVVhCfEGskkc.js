(function ($) {

$(document).ready(function() {

  // Expression to check for absolute internal links.
  var isInternal = new RegExp("^(https?):\/\/" + window.location.host, "i");

  // Attach onclick event to document only and catch clicks on all elements.
  $(document.body).click(function(event) {
    // Catch the closest surrounding link of a clicked element.
    $(event.target).closest("a,area").each(function() {

      var ga = Drupal.settings.googleanalytics;
      // Expression to check for special links like gotwo.module /go/* links.
      var isInternalSpecial = new RegExp("(\/go\/.*)$", "i");
      // Expression to check for download links.
      var isDownload = new RegExp("\\.(" + ga.trackDownloadExtensions + ")$", "i");

      // Is the clicked URL internal?
      if (isInternal.test(this.href)) {
        // Skip 'click' tracking, if custom tracking events are bound.
        if ($(this).is('.colorbox')) {
          // Do nothing here. The custom event will handle all tracking.
        }
        // Is download tracking activated and the file extension configured for download tracking?
        else if (ga.trackDownload && isDownload.test(this.href)) {
          // Download link clicked.
          var extension = isDownload.exec(this.href);
          _gaq.push(["_trackEvent", "Downloads", extension[1].toUpperCase(), this.href.replace(isInternal, '')]);
        }
        else if (isInternalSpecial.test(this.href)) {
          // Keep the internal URL for Google Analytics website overlay intact.
          _gaq.push(["_trackPageview", this.href.replace(isInternal, '')]);
        }
      }
      else {
        if (ga.trackMailto && $(this).is("a[href^='mailto:'],area[href^='mailto:']")) {
          // Mailto link clicked.
          _gaq.push(["_trackEvent", "Mails", "Click", this.href.substring(7)]);
        }
        else if (ga.trackOutbound && this.href.match(/^\w+:\/\//i)) {
          if (ga.trackDomainMode == 2 && isCrossDomain(this.hostname, ga.trackCrossDomains)) {
            // Top-level cross domain clicked. document.location is handled by _link internally.
            event.preventDefault();
            _gaq.push(["_link", this.href]);
          }
          else {
            // External link clicked.
            _gaq.push(["_trackEvent", "Outbound links", "Click", this.href]);
          }
        }
      }
    });
  });

  // Colorbox: This event triggers when the transition has completed and the
  // newly loaded content has been revealed.
  $(document).bind("cbox_complete", function() {
    var href = $.colorbox.element().attr("href");
    if (href) {
      _gaq.push(["_trackPageview", href.replace(isInternal, '')]);
    }
  });

});

/**
 * Check whether the hostname is part of the cross domains or not.
 *
 * @param string hostname
 *   The hostname of the clicked URL.
 * @param array crossDomains
 *   All cross domain hostnames as JS array.
 *
 * @return boolean
 */
function isCrossDomain(hostname, crossDomains) {
  /**
   * jQuery < 1.6.3 bug: $.inArray crushes IE6 and Chrome if second argument is
   * `null` or `undefined`, http://bugs.jquery.com/ticket/10076,
   * https://github.com/jquery/jquery/commit/a839af034db2bd934e4d4fa6758a3fed8de74174
   *
   * @todo: Remove/Refactor in D8
   */
  if (!crossDomains) {
    return false;
  }
  else {
    return $.inArray(hostname, crossDomains) > -1 ? true : false;
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
(function ($) {
  Drupal.behaviors.ws_lsb = {
    attach: function (context, settings) {
      $('a.service-links-linkedin-share-button', context).each(function(){
        var script_obj = document.createElement('script');
        script_obj.type = 'IN/Share';
        script_obj.setAttribute("data-url", $(this).attr('href'));
        if (Drupal.settings.ws_lsb.countmode != '') {
          script_obj.setAttribute("data-counter", Drupal.settings.ws_lsb.countmode);
        }
        $(this).replaceWith(script_obj);
      });

      try {
        IN.init({
          onLoad: "Drupal.behaviors.ws_lsb.parse"
        });
      }
      catch(e) {
        if (window.console && window.console.log) {
          console.log(e);
        }
      }
    },

    parse: function(context) {
      try {
        IN.parse(context);
      }
      catch(e) {
        if (window.console && window.console.log) {
          console.log(e);
        }
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
