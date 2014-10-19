<?php

/**
 * The class used for real_estate_property entities
 */
class RealEstatePropertyEntity extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'real_estate_property');
  }

  protected function defaultLabel() {
    return $this->name;
  }

  protected function defaultUri() {
    return array('path' => 'real_estate_property/' . $this->property_id);
  }


}


/**
 * The class used for real_estate_property type entities
 */
class RealEstatePropertyTypeEntity extends Entity {

  public $type;
  public $label;

  public function __construct($values = array()) {
    parent::__construct($values, 'real_estate_property_type');
  }

}


/**
 * Function for converting an addressfield data format to a string.
 *
 * @param $address
 *   - a data in an addressfield format
 *
 * @return string
 *   - a address in a string format
 */
function real_estate_property_convert_address($address) {
  $handlers = array('address' => 'address');
  $context = array('mode' => 'render');

  $address = addressfield_generate($address, $handlers, $context);
  $address = drupal_render($address);

  // Add some commas for parsing an address by Google Map's API.
  $address = preg_replace('/(<\/[^>]+?>)(<[^>\/][^>]*?>)/', '$1, $2', $address);
  $address = strip_tags($address);

  return $address;
}
