Drupal Real Estate (DRE) is a solution for the creation of a real estate and
property classifieds sites.

Note: the module is under active development and for now is available only basic
functionality. Soon will be available much more.

INSTALLATION

Short description:

The module provides easy installation:
1. Download all required modules and libraries.
2. Enable the Kickstart module.
3. Go to a Real Estate menu.

Full description:

1. Download required modules:
  Entity API - http://drupal.org/project/entity

  Views - http://drupal.org/project/views

  Address Field - http://drupal.org/project/addressfield

  CTools - http://drupal.org/project/ctools

  Libraries API 2.x - http://drupal.org/project/libraries

  Flex Slider (version 7.x-2.0-alpha3) - http://drupal.org/project/flexslider
  FlexSlider library (version 2.2.0) -  https://github.com/woothemes/FlexSlider
    Unzip the file, rename the folder to "flexslider" and move to
    the sites/all/libraries folder.
    For more details, please, visit http://drupal.org/project/flexslider

    For using the FlexSlider library of version higher then 2.2.0 is needed to use JQuery 1.7 or higher.
    For that can be used modules jQuery Update (jquery_update) or jQuery Multi (jqmulti).

2. Then go to the Real Estate section and enable a DRE Kickstart module
  if you want use the whole DRE package.

3. Go to the Real Estate menu (admin/real_estate) in the admin area.
  Visit the property demo page /real_estate_property/1
  For adding property types go to /admin/real_estate/property_type
  For adding property go to /admin/real_estate/property/add
  After adding property it will be accessible from a page /real-estate-property-list


  Instead of using a Flex Slider module, can be used any other slider module.

  Instead of using the DRE SimpleGMap module, can be used more complex and
  powerful solution. Addressfield address can be automatically Geocoded into
  Geofield points for display on Openlayers Maps.


FUTURE DEVELOPMENT

  Agents
  Rental
  MLS integration


