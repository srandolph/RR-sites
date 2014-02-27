<?php

/**
 * @file
 * The controller for the property entity containing the CRUD operations.
 */

/**
 * The controller class contains methods for the property CRUD operations.
 */
class RealEstatePropertyTypeEntityController extends EntityAPIControllerExportable {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

   /**
   * Create a real_estate_property type
   *
   * @param $type
   *   The machine-readable type of the real_estate_property.
   *
   * @return
   *   A real_estate_property type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our real_estate_property
    $values += array(
      'type' => '',
      'label' => '',
      'description' => '',
      'revision' => 1,
      'is_new' => TRUE,
    );
    $real_estate_property_type = parent::create($values);
    return $real_estate_property_type;
  }


}
