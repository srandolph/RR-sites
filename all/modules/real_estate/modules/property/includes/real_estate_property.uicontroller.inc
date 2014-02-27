<?php

/**
 * @file
 * Property editing UI.
 *
 */

/**
 * UI controller.
 */
class RealEstatePropertyUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Property',
      'description' => 'Add edit and update real_estate_property.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Change the overview menu type for the list of real_estate_property.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a Property',
      'description' => 'Add a new real_estate_property',
      'page callback'  => 'real_estate_property_add_page',
      'access callback'  => 'real_estate_property_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'real_estate_property.uicontroller.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']) . '/includes'

    );

    // Add menu items to add each different type of entity.
    foreach (real_estate_property_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'real_estate_property_form_wrapper',
        'page arguments' => array(real_estate_property_create(array('type' => $type->type))),
        'access callback' => 'real_estate_property_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'real_estate_property.uicontroller.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module']) . '/includes'
      );
    }

    // Loading and editing real_estate_property entities
    $items[$this->path . '/' . $wildcard] = array(
      'page callback' => 'real_estate_property_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'real_estate_property_access',
      'access arguments' => array('edit', $id_count),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'real_estate_property.uicontroller.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']) . '/includes'
    );
    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'real_estate_property_delete_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'real_estate_property_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'real_estate_property.uicontroller.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']) . '/includes'
    );

    // Menu item for viewing real_estate_property
    $items['real_estate_property/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'real_estate_property_page_title',
      'title arguments' => array(1),
      'page callback' => 'real_estate_property_page_view',
      'page arguments' => array(1),
      'access callback' => 'real_estate_property_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


  /**
   * Create the markup for the add real_estate_property Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('real_estate_property_add_list', array('content' => $content));
  }

}


/**
 * Form callback wrapper: create or edit a real_estate_property.
 *
 * @param $real_estate_property
 *   The real_estate_property object being edited by this form.
 *
 * @see real_estate_property_edit_form()
 */
function real_estate_property_form_wrapper($real_estate_property) {
  // Add the breadcrumb for the form's location.
  real_estate_property_set_breadcrumb();
  return drupal_get_form('real_estate_property_edit_form', $real_estate_property);
}


/**
 * Form callback wrapper: delete a real_estate_property.
 *
 * @param $real_estate_property
 *   The real_estate_property object being edited by this form.
 *
 * @see real_estate_property_edit_form()
 */
function real_estate_property_delete_form_wrapper($real_estate_property) {
  // Add the breadcrumb for the form's location.
  //real_estate_property_set_breadcrumb();
  return drupal_get_form('real_estate_property_delete_form', $real_estate_property);
}


/**
 * Form callback: create or edit a real_estate_property.
 *
 * @param $real_estate_property
 *   The real_estate_property object to edit or for a create form an empty real_estate_property object
 *     with only a real_estate_property type defined.
 */
function real_estate_property_edit_form($form, &$form_state, $real_estate_property) {
  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Property Name'),
    '#default_value' => isset($real_estate_property->title) ? $real_estate_property->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  $form['data']['#tree'] = TRUE;

  // Add the field related form elements.
  $form_state['real_estate_property'] = $real_estate_property;
  field_attach_form('real_estate_property', $real_estate_property, $form, $form_state);

  // Load the default revision setting.
  $property_type = real_estate_property_type_load($real_estate_property->type);

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
  if (!empty($real_estate_property->property_id)) {
    $form['history']['revision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Create new revision'),
      '#description' => t(''),
//      '#default_value' => $property_type['revision'],
      '#access' => user_access('administer property'),
    );
  }

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 500,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Property'),
    '#submit' => $submit + array('real_estate_property_edit_form_submit'),
  );

  if (!empty($real_estate_property->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete real_estate_property'),
      '#suffix' => l(t('Cancel'), 'admin/content/real_estate_property'),
      '#submit' => $submit + array('real_estate_property_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'real_estate_property_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the real_estate_property form
 */
function real_estate_property_edit_form_validate(&$form, &$form_state) {
  $real_estate_property = $form_state['real_estate_property'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('real_estate_property', $real_estate_property, $form, $form_state);
}


/**
 * Form API submit callback for the real_estate_property form.
 *
 */
function real_estate_property_edit_form_submit(&$form, &$form_state) {

  $real_estate_property = entity_ui_controller('real_estate_property')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the real_estate_property and go back to the list of real_estate_property

  // Add in created and changed times.
  if ($real_estate_property->is_new = isset($real_estate_property->is_new) ? $real_estate_property->is_new : 0){
    $real_estate_property->created = time();
  }

  $real_estate_property->changed = time();

  if ((user_access('administer property') && !empty($form_state['values']['revision']))) {
    $real_estate_property->revision = TRUE; // enable revision
  }

  $real_estate_property->save();
  $form_state['redirect'] = 'admin/real_estate/property';
}

/**
 * Form API submit callback for the delete button.
 */
function real_estate_property_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/real_estate/real_estate_property/real_estate_property/' . $form_state['real_estate_property']->real_estate_property_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a real_estate_property.
 *
 * @param $real_estate_property
 *   The real_estate_property to delete
 *
 * @see confirm_form()
 */
function real_estate_property_delete_form($form, &$form_state, $real_estate_property) {
  $form_state['real_estate_property'] = $real_estate_property;

  $form['#submit'][] = 'real_estate_property_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete real_estate_property %name?', array('%name' => $real_estate_property->name)),
    'admin/content/real_estate_property/real_estate_property',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for real_estate_property_delete_form
 */
function real_estate_property_delete_form_submit($form, &$form_state) {
  $real_estate_property = $form_state['real_estate_property'];

  real_estate_property_delete($real_estate_property);

  drupal_set_message(t('The property %name has been deleted.', array('%name' => $real_estate_property->name)));
  watchdog('real_estate_property', 'Deleted property %name.', array('%name' => $real_estate_property->name));

  $form_state['redirect'] = 'admin/content/real_estate_property';
}


/**
 * Page to add real_estate_property Entities.
 */
function real_estate_property_add_page() {
  $controller = entity_ui_controller('real_estate_property');
  return $controller->addPage();
}


/**
 * Displays the list of available real_estate_property types for real_estate_property creation.
 *
 * @ingroup themeable
 */
function theme_real_estate_property_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="real_estate_property-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer real_estate_property types')) {
      $output = '<p>' . t('Property Entities cannot be added because you have not created any real_estate_property types yet. Go to the <a href="@create-real_estate_property-type">real_estate_property type creation page</a> to add a new real_estate_property type.', array('@create-real_estate_property-type' => url('admin/structure/real_estate_property_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No property types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative real_estate_property pages.
 */
function real_estate_property_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Property'), 'admin/content/real_estate_property'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



