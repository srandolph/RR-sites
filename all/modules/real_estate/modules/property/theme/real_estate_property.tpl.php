<?php

/**
 * @file
 * A basic template for real_estate_property entities
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>

  <div id="real-estate-media">
    <?php
    print render($content['property_photo']);
    ?>
  </div>
  <div id="real-estate-values">
    <?php
    print render($content['property_price']);
    print render($content['property_address']);
    print render($content['property_bathrooms']);
    print render($content['property_bedrooms']);
    print render($content['property_yearbuilt']);
    print render($content['property_lot_size']);
    ?>
  </div>
  <div id="real-estate-description">
    <?php
    print render($content['property_description']);
    ?>
  </div>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
    hide($content['property_photo']);
    print render($content);
    ?>
  </div>


</div>
