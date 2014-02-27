<?php

/**
 * This field handler aggregates operations that can be done on a real_estate_property
 * under a single field providing a more flexible way to present them in a view
 */
class real_estate_property_handler_real_estate_property_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['property_id'] = 'property_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('real_estate_property', 'admin/real_estate/property', array($this->get_value($values, 'property_id')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
