<?php

/**
 * Migration class used to import Default Data Stories from fixtures.
 */
class DefaultContentPagesImport extends DkanPagesImport {

  /**
   * __construct().
   */
  public function __construct($arguments) {

    if (!isset($arguments['endpoint'])) {
      $arguments['endpoint'] = drupal_get_path('module', 'dkan_default_content') . '/data/';
      $arguments['list_url'] = 'page_list.json';
      $arguments['item_url'] = 'page_show?id=:id.json';
    }

    parent::__construct($arguments);
  }

  /**
   * Prepare row data for import.
   */
  public function prepareRow($row) {
    // Skip import of page if there is another one with the same UUID.
    $page = reset(entity_get_id_by_uuid('node', array($row->uuid)));
    if ($page) {
      return false;
    }

    parent::prepareRow($row);
  }

  /**
   * Do extra processing after import.
   */
  public function complete($entity, $row) {

    parent::complete($entity, $row);

    if (isset($row->is_homepage)) {
      // Setup imported page as the homepage.
      variable_set('site_frontpage', 'node/' . $entity->nid);
    } else {
      // Setup menu item on main menu.
      $this->addMainMenuLink($entity);
    }
  }

  /**
   * Add a menu link on Main Menu for entity.
   */
  private function addMainMenuLink($entity) {
    $item = array(
      'menu_name' => 'main-menu',
      'link_path' => 'node/' . $entity->nid,
      'router_path' => 'node/%',
      'link_title' => $entity->title,
      'options' => array(
        'attributes' => array(
          'title' => '',
        ),
        'identifier' => 'main-menu_about:node/' . $entity->nid,
      ),
      'module' => 'menu',
      'hidden' => 0,
      'external' => 0,
      'has_children' => 0,
      'expanded' => 0,
      'weight' => 0,
      'customized' => 1,
    );
    menu_link_save($item);
  }
}