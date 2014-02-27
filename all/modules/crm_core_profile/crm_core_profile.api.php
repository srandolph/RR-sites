<?php

/**
 * @file
 * Describes hooks used in CRM Core Profile
 */

/**
 * Registers an entity handler within CRM Core Profile
 *
 * This hook is used whenever you want to register an entity handler with CRM
 * Core Profile. The function should pass back an associative array, where the
 * key is a unique name for the entity handler, and the value is the name of the
 * object used to handle the entity.
 */
function hook_crm_core_profile_register_entity(){
  return array(
    'commerce_product' => 'CommerceProfileHandler',
  );
}

/**
 * Fires just before a contact is saved through a CRM Core Profile.
 *
 * This hook is necessary because of the way CRMCoreContactEntity->match works.
 * When checking for duplicates, CRM Core provides the ability to modify a contact record
 * during the matching process. CRM Core Profile will update any contact record values
 * that are passed into the form, but it will not necessarily carry over any changes to
 * contact records that have been made via CRMCoreContactEntity->match.
 *
 * This scenario will not affect profiles that are prepopulated, or profiles that do not
 * use contact matching.
 *
 * Of course, this hook can be used for other reasons as well. Use it any time you need to
 * modify a value being stored as part of a contact record before it is saved. For instance,
 * if you need a store the source of a contact, this might be a good way to do it.
 *
 * This hook takes an associative array of values, which includes the contact record passed
 * by reference. Any modifications to the contact record will be saved when the contact is
 * saved through the profile.
 *
 * @param array $values
 * An associative array, including a key for the contact record passed by reference.
 */
function hook_crm_core_profile_contact_presave(&$values){

  $contact = $values['contact'];

  // when modifying a contact record, you could store the modifications in a static variable...
  $my_custom_changes = & drupal_static(__FUNCTION__);

  // ... and check to make sure they are staged to be committed. This would eliminate any issues
  // with modifications that are being made to existing contacts.
  if(isset($my_custom_changes[$values['contact']->contact_id]) && !isset($values['contact']->my_custom_changes)){
    $values['contact']->my_custom_changes = $my_custom_changes[$values['contact']->contact_id];
  }

}

/**
 * Fires before token replacement in fields gathered by profile form submission.
 *
 * See token_replace() for $context description.
 *
 * @param array $context
 *   Array of entities keyed by entity specific token type.
 *
 * @see token_replace()
 */
function hook_crm_core_profile_before_token_replace_alter(&$context) {
  if (isset($context['commerce-product'])) {
    unset($context['commerce-product']);
  }
}
