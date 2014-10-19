<?php

/**
 * @file
 * Real Estate Property views.
 */

/**
 * Implements hook_views_data().
 */
function real_estate_property_views_data_alter(&$data) {
  $data['real_estate_property']['link_real_estate_property'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the real_estate_property.'),
      'handler' => 'real_estate_property_handler_link_field',
    ),
  );
  $data['real_estate_property']['edit_real_estate_property'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the real_estate_property.'),
      'handler' => 'real_estate_property_handler_edit_link_field',
    ),
  );
  $data['real_estate_property']['delete_real_estate_property'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the real_estate_property.'),
      'handler' => 'real_estate_property_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows real_estate_property/real_estate_property/%property_id/op
  $data['real_estate_property']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this real_estate_property.'),
      'handler' => 'real_estate_property_handler_real_estate_property_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function real_estate_property_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'real_estate_property';
  $view->description = 'A list of all property';
  $view->tag = 'RE - property list';
  $view->base_table = 'real_estate_property';
  $view->human_name = 'Real Estate - Property';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Real Estate - Property';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any real_estate_property type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'property_id' => 'property_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'property_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['content'] = 'No real_estate_property have been created yet';
  /* Field: Property: Property ID */
  $handler->display->display_options['fields']['property_id']['id'] = 'property_id';
  $handler->display->display_options['fields']['property_id']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['property_id']['field'] = 'property_id';
  /* Field: Property: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Property: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Property: Link */
  $handler->display->display_options['fields']['link_real_estate_property']['id'] = 'link_real_estate_property';
  $handler->display->display_options['fields']['link_real_estate_property']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['link_real_estate_property']['field'] = 'link_real_estate_property';
  $handler->display->display_options['fields']['link_real_estate_property']['label'] = 'View';
  /* Field: Property: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'real_estate_property_admin_page');
  $handler->display->display_options['path'] = 'admin/real_estate/property/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Property';
  $handler->display->display_options['tab_options']['description'] = 'Manage the Property';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  $views[] = $view;

  //
  // Show list of property.

  $view = new view();
  $view->name = 'real_estate_property_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'real_estate_property';
  $view->human_name = 'Real Estate Property List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Real Estate Property List';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    1 => '1',
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'property_photo' => 'property_photo',
    'property_address' => 'property_address',
    'property_bathrooms' => 'property_bathrooms',
    'property_bedrooms' => 'property_bedrooms',
    'property_price' => 'property_price',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'property_photo' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'property_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'property_bathrooms' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'property_bedrooms' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'property_price' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Property: Property ID */
  $handler->display->display_options['fields']['property_id']['id'] = 'property_id';
  $handler->display->display_options['fields']['property_id']['table'] = 'real_estate_property';
  $handler->display->display_options['fields']['property_id']['field'] = 'property_id';
  $handler->display->display_options['fields']['property_id']['label'] = '';
  $handler->display->display_options['fields']['property_id']['element_label_colon'] = FALSE;
  /* Field: Property: Photo */
  $handler->display->display_options['fields']['property_photo']['id'] = 'property_photo';
  $handler->display->display_options['fields']['property_photo']['table'] = 'field_data_property_photo';
  $handler->display->display_options['fields']['property_photo']['field'] = 'property_photo';
  $handler->display->display_options['fields']['property_photo']['label'] = '';
  $handler->display->display_options['fields']['property_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['property_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['property_photo']['settings'] = array(
    'image_style' => 'real_estate_property_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['property_photo']['delta_limit'] = '1';
  $handler->display->display_options['fields']['property_photo']['delta_offset'] = '0';
  /* Field: Property: Address */
  $handler->display->display_options['fields']['property_address']['id'] = 'property_address';
  $handler->display->display_options['fields']['property_address']['table'] = 'field_data_property_address';
  $handler->display->display_options['fields']['property_address']['field'] = 'property_address';
  $handler->display->display_options['fields']['property_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['property_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Property: Bathrooms */
  $handler->display->display_options['fields']['property_bathrooms']['id'] = 'property_bathrooms';
  $handler->display->display_options['fields']['property_bathrooms']['table'] = 'field_data_property_bathrooms';
  $handler->display->display_options['fields']['property_bathrooms']['field'] = 'property_bathrooms';
  /* Field: Property: Bedrooms */
  $handler->display->display_options['fields']['property_bedrooms']['id'] = 'property_bedrooms';
  $handler->display->display_options['fields']['property_bedrooms']['table'] = 'field_data_property_bedrooms';
  $handler->display->display_options['fields']['property_bedrooms']['field'] = 'property_bedrooms';
  /* Field: Property: Price */
  $handler->display->display_options['fields']['property_price']['id'] = 'property_price';
  $handler->display->display_options['fields']['property_price']['table'] = 'field_data_property_price';
  $handler->display->display_options['fields']['property_price']['field'] = 'property_price';
  $handler->display->display_options['fields']['property_price']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Filter criterion: Property: Address (property_address:postal_code) */
  $handler->display->display_options['filters']['property_address_postal_code']['id'] = 'property_address_postal_code';
  $handler->display->display_options['filters']['property_address_postal_code']['table'] = 'field_data_property_address';
  $handler->display->display_options['filters']['property_address_postal_code']['field'] = 'property_address_postal_code';
  $handler->display->display_options['filters']['property_address_postal_code']['group'] = 1;
  $handler->display->display_options['filters']['property_address_postal_code']['exposed'] = TRUE;
  $handler->display->display_options['filters']['property_address_postal_code']['expose']['operator_id'] = 'property_address_postal_code_op';
  $handler->display->display_options['filters']['property_address_postal_code']['expose']['label'] = 'Postal code';
  $handler->display->display_options['filters']['property_address_postal_code']['expose']['operator'] = 'property_address_postal_code_op';
  $handler->display->display_options['filters']['property_address_postal_code']['expose']['identifier'] = 'property_address_postal_code';
  $handler->display->display_options['filters']['property_address_postal_code']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Property: Address (property_address:country) */
  $handler->display->display_options['filters']['property_address_country']['id'] = 'property_address_country';
  $handler->display->display_options['filters']['property_address_country']['table'] = 'field_data_property_address';
  $handler->display->display_options['filters']['property_address_country']['field'] = 'property_address_country';
  $handler->display->display_options['filters']['property_address_country']['group'] = 1;
  $handler->display->display_options['filters']['property_address_country']['exposed'] = TRUE;
  $handler->display->display_options['filters']['property_address_country']['expose']['operator_id'] = 'property_address_country_op';
  $handler->display->display_options['filters']['property_address_country']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['property_address_country']['expose']['operator'] = 'property_address_country_op';
  $handler->display->display_options['filters']['property_address_country']['expose']['identifier'] = 'property_address_country';
  $handler->display->display_options['filters']['property_address_country']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Property: Address (property_address:administrative_area) */
  $handler->display->display_options['filters']['property_address_administrative_area']['id'] = 'property_address_administrative_area';
  $handler->display->display_options['filters']['property_address_administrative_area']['table'] = 'field_data_property_address';
  $handler->display->display_options['filters']['property_address_administrative_area']['field'] = 'property_address_administrative_area';
  $handler->display->display_options['filters']['property_address_administrative_area']['operator'] = 'contains';
  $handler->display->display_options['filters']['property_address_administrative_area']['group'] = 1;
  $handler->display->display_options['filters']['property_address_administrative_area']['exposed'] = TRUE;
  $handler->display->display_options['filters']['property_address_administrative_area']['expose']['operator_id'] = 'property_address_administrative_area_op';
  $handler->display->display_options['filters']['property_address_administrative_area']['expose']['label'] = 'Administrative area';
  $handler->display->display_options['filters']['property_address_administrative_area']['expose']['operator'] = 'property_address_administrative_area_op';
  $handler->display->display_options['filters']['property_address_administrative_area']['expose']['identifier'] = 'property_address_administrative_area';
  $handler->display->display_options['filters']['property_address_administrative_area']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Property: Price (property_price) */
  $handler->display->display_options['filters']['property_price_value']['id'] = 'property_price_value';
  $handler->display->display_options['filters']['property_price_value']['table'] = 'field_data_property_price';
  $handler->display->display_options['filters']['property_price_value']['field'] = 'property_price_value';
  $handler->display->display_options['filters']['property_price_value']['operator'] = 'between';
  $handler->display->display_options['filters']['property_price_value']['group'] = 1;
  $handler->display->display_options['filters']['property_price_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['property_price_value']['expose']['operator_id'] = 'property_price_value_op';
  $handler->display->display_options['filters']['property_price_value']['expose']['label'] = 'Price';
  $handler->display->display_options['filters']['property_price_value']['expose']['operator'] = 'property_price_value_op';
  $handler->display->display_options['filters']['property_price_value']['expose']['identifier'] = 'property_price_value';
  $handler->display->display_options['filters']['property_price_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['property_price_value']['group_info']['label'] = 'Price (property_price)';
  $handler->display->display_options['filters']['property_price_value']['group_info']['identifier'] = 'property_price_value';
  $handler->display->display_options['filters']['property_price_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => '',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
    2 => array(
      'title' => '',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => 'between',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'real-estate-property-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Real Estate';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[] = $view;

  return $views;

}
