(function ($) {
  Drupal.behaviors.dennisclientModule = {
    attach: function (context, settings) {
      $("#edit-field-content-partnerships-und").change(function() {
        // Exclude the content from the xml sitemap if  a term in content partnerships has been selected.
        if (this.value != "_none") {
          $('#edit-xmlsitemap-status option[value=0]').prop('selected', 'selected');
          status = 0;
        }
        else {
          $('#edit-xmlsitemap-status option[value=1]').prop('selected', 'selected');
          status = 1;
        }
        // Remove all selected from options.
        $("#edit-xmlsitemap-status option").attr('selected', false);
        // Add select attribute to the chosen option.
        $("#edit-xmlsitemap-status option[value=" + status + "]").attr('selected','selected');
      });
    }
  };
}(jQuery));
