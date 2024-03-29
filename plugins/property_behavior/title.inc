<?php
/**
 * @file
 * The title behavior makes a property behave like a title.
 *
 * 1) When then entity is view, we set the page title to be the
 *    properties value.
 * 2) We set the property as the label of the entity.
 * 3) The property can be entered by the user with a text field.
 * 4) The property is displayed as an h1 tag.
 */

$plugin = array(
  'label' => "Title",
  'entity_label' => 'eck_title_property_entity_label',
  'entity_view' => 'eck_title_property_entity_view',
  'entity_info' => 'eck_title_property_entity_info',
  'default_widget' => 'eck_title_property_widget',
);

/**
 * How to input a title.
 */
function eck_title_property_widget($property, $vars) {
  $entity = $vars['entity'];
  $title = _eck_title_property_extract_title($entity, $property);
  return array(
    '#type' => 'textfield',
    '#title' => $vars['properties'][$property]['label'],
    '#maxlength' => 255,
    '#default_value' => $title,
    '#required' => TRUE,
  );
}

/**
 * When we are viewing the entity, set the pages title.
 */
function eck_title_property_entity_view($property, $vars) {
  $entity = $vars['entity'];
  $title = _eck_title_property_extract_title($entity, $property);

  if (empty($title)) {
    $entity_id = $entity->id();
    $title = "{$entity->entityType()} : {$entity_id}";
  }

  $uri = entity_uri($entity->entityType(), $entity);
  if ($uri['path'] == current_path()) {
    backdrop_set_title($title);
  }
}

/**
 * Set the entity label.
 */
function eck_title_property_entity_label($property, $vars) {
  $entity = $vars['entity'];
  $title = _eck_title_property_extract_title($entity, $property);

  if (empty($title)) {
    $entity_id = $entity->id();
    $title = "{$entity->entityType()} : {$entity_id}";
  }

  return $title;
}

/**
 * Make whatever property is using the title behavior, the label.
 */
function eck_title_property_entity_info($property, $var) {
  $info = $var;
  unset($info['label callback']);
  $info['entity keys']['label'] = $property;

  return $info;
}

/**
 * Helper function that gets the title from an entity.
 *
 * @param object $entity
 *   an entity object.
 * @param string $property
 *   the name of the property that contains the title.
 *
 * @return string
 *   The title of the entity.
 */
function _eck_title_property_extract_title($entity, $property) {
  $title = "";
  if (isset($entity->{$property})) {
    $title = $entity->{$property};
  }

  return $title;
}
