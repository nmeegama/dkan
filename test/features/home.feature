Feature: Homepage
  In order to know the website is running
  As a website user
  I need to be able to view the site title and login
  
  @customizable
  Scenario: Viewing the site title
    Given I am on the homepage
    Then I should see "Welcome to DKAN"

  @customizable
  Scenario: Viewing top menu
    Given I am on the homepage
    Then I should see "Datasets"
    And I should see "Groups"
    And I should see "About"
    And I should see "Topics"
    And I should see "Stories"
    And I should see "Dashboards"

  @customizable
  Scenario: Viewing sections
    Given I am on the homepage
    Then I should see "Latest Data Stories" in the "content" region
    And I should see "Groups" in the "content" region
    And I should see "Dashboards" in the "content" region

  @api @javascript @customizable
  Scenario: See "Add Dataset"
    Given I am logged in as a user with the "content creator" role
    And I am on the homepage
    Then I hover over the admin menu item "Content"
    Then I hover over the admin menu item "Add content"
    Then I should see the admin menu item "Dataset"

  @api @javascript
  Scenario: See "Dataset Form"
    Given I am logged in as a user with the "content creator" role
    And I am on the homepage
    Then I hover over the admin menu item "Content"
    Then I hover over the admin menu item "Add content"
    Then I click "Dataset"
    Then I should see "Create Dataset"
