<?php

/**
 * @file
 * The controller for the property entity containing the CRUD operations.
 */

/**
 * The controller class contains methods for the property CRUD operations.
 */
class RealEstatePropertyEntityController extends EntityAPIController {

  /**
   * Create a default property.
   *
   * @param array $values
   *   An array of values to set, keyed by name.
   * @return
   *   A property object with all default fields initialized.
   */
  public function create(array $values = array()) {
    global $user;

    $values += array(
      'property_id' => NULL,
      'is_new' => TRUE,
      'revision_id' => NULL,
      'title' => '',
      'uid' => $user->uid,
      'status' => 1,
      'created' => '',
      'changed' => '',
      'log' => '',
    );

    return parent::create($values);
  }


}
