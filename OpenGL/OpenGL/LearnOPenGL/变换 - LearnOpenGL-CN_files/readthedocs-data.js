var READTHEDOCS_DATA = {
    "programming_language": "cpp", 
    "user_analytics_code": "", 
    "docroot": "docs", 
    "global_analytics_code": "UA-17997319-1", 
    "source_suffix": ".md", 
    "api_host": "https://readthedocs.org", 
    "language": "zh", 
    "builder": "mkdocs", 
    "project": "learnopengl-cn", 
    "theme": "readthedocs", 
    "version": "latest", 
    "commit": "09b7161567fb98eff107ac9bcb7835608551910f", 
    "page": null
}

// Old variables
var doc_version = "latest";
var doc_slug = "learnopengl-cn";
var page_name = "None";
var html_theme = "readthedocs";

READTHEDOCS_DATA["page"] = mkdocs_page_input_path.substr(
    0, mkdocs_page_input_path.lastIndexOf(READTHEDOCS_DATA.source_suffix));
