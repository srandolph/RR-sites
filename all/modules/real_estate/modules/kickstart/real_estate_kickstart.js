(function($) {
  Drupal.behaviors.realestateKickStart = {
    attach: function (context, settings) {

      $("#edit-calculate-2").once('mortgageCalculator', function(){
        Drupal.MCalculator.cmdCalc_Click(this.form);
      });

    }
  }
})(jQuery);
