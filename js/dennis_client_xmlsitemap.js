(function ($) {
  Drupal.behaviors.dennisclientModule = {
    attach: function (context, settings) {
      $("#edit-field-content-partnerships-und").change(function() {
        // Exclude the content from the xml sitemap if  a term in content partnerships has been selected.
        if (this.value != "_none") {
          $('#edit-xmlsitemap-status option[value=0]').prop('selected', 'selected');
        }
        else {
          $('#edit-xmlsitemap-status option[value=1]').prop('selected', 'selected')
        }
      });
    }
  };
}(jQuery));
