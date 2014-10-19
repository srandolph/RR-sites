<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */

class real_estate_property_handler_delete_link_field extends real_estate_property_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};

    // Creating a dummy real_estate_property to check access against.
    $dummy_real_estate_property = (object) array('type' => $type);
    if (!real_estate_property_access('edit', $dummy_real_estate_property)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $property_id = $values->{$this->aliases['property_id']};

    return l($text, 'admin/content/real_estate_property/real_estate_property/' . $property_id . '/delete');
  }
}
