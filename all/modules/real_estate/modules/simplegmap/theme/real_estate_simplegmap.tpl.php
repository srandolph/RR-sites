<?php $size = explode('x', $settings['size']); ?>

<div id="map_canvas" style="width: <?php print $size[0]; ?>px; height: <?php print $size[1]; ?>px;">
  <noscript>
    <?php print theme_image(array('path' => $settings['simplegmap_url'], 'attributes' => array('class' => 'static_google_map'))); ?>
  </noscript>
</div>


