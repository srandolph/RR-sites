<?php

/**
 * @file
 * Real Estate type editing UI.
 */

/**
 * UI controller.
 */
class RealEstatePropertyTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage property types.';
    $items[$this->path]['weight'] = '2';
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    return $items;
  }
}

/**
 * Generates the Real Estate property editing form.
 */
function real_estate_property_type_form($form, &$form_state, $real_estate_property_type, $op = 'edit') {

  if ($op == 'clone') {
    $real_estate_property_type->label .= ' (cloned)';
    $real_estate_property_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Property type'),
    '#type' => 'textfield',
    '#default_value' => $real_estate_property_type->label,
    '#description' => t('The human-readable name of this property type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($real_estate_property_type->type) ? $real_estate_property_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'real_estate_property_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this property type. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => $real_estate_property_type->description,
    '#description' => t('Short description.'),
    '#size' => 30,
  );
  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );
  $form['history'] = array(
    '#type' => 'fieldset',
    '#title' => t('Change history'),
    '#collapsible' => TRUE,
    '#weight' => 40,
    '#group' => 'additional_settings',
  );
  $form['history']['revision'] = array(
    '#title' => t('Revision'),
    '#type' => 'checkbox',
    '#default_value' => $real_estate_property_type->revision,
    '#description' => t('Enable revision.'),
  );
  $form['data']['#tree'] = TRUE;

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Real Estate Property type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the property form.
 */
function real_estate_property_type_form_submit(&$form, &$form_state) {
  $real_estate_property_type = entity_ui_form_submit_build_entity($form, $form_state);
  $real_estate_property_type->save();

  // add fields Address Photo and Price
  if($form_state['op'] == 'add') {
    _real_estate_property_type_add_few_fields($real_estate_property_type->type);
  }

  $form_state['redirect'] = 'admin/real_estate/property_type';
}

/**
 * Form API submit callback for the delete button.
 */
function real_estate_property_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/real_estate/property_type/manage/' . $form_state['real_estate_property']->type . '/delete';

}

