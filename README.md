INTRODUCTION
------------

Provides the following:
 * DFP targeting for Client terms
 * A Content partnership block that can be attached to articles
 * When the module is installed, some fields will be created on specific content
   types: Article, Review, Advanced Gallery.

   If a given content type is not available when the module is installed, the
   fields will be attached to the content type anytime it becomes available.

   The following fields will be attached to the content types:
   * Client: A taxonomy term reference to Client term.

     Client taxonomy contains Content sponsorship fields that allow us to specify:
     * Intro text
     * Company name
     * Logo
     * Link
     * Strap line
     * Enable branding on nodes: Global switch to enable the block on all nodes
       It is possible to turn off the block on node level, see below.
       When a client is selected, the two fields below will become available.

   * Content Partnership: A term reference for Content Partnerships.
     See admin/help/dennis_client/tips#content-partnership

   * Exclude client branding on this node: Do not show the block on this node

 * Sponsored content is excluded from News sitemaps.
 * Sponsored content is outputted on Google analytics custom dimension2.

REQUIREMENTS
------------

 * Features
 * File Entity
 * Link
 * Strongarm
 * Taxonomy

INSTALLATION
------------

 * Enable the module as usual
 * Add Client terms admin/structure/taxonomy/clients
 * Create an article and select the client.

FAQ
---

To attach fields programmatically to a new content type:

// Get existing configuration.
$bundles = variable_get('dennis_client_bundles');
// Add new content type.
$bundles[] = 'content_type';
// Update configuration.
variable_set('dennis_client_bundles', $bundles);

When you do this, the hook_node_type_insert() will pick up the configuration and attach the fields automatically.

Also, see the <a href="/admin/help/dennis_client/tips">Tips</a> page.
