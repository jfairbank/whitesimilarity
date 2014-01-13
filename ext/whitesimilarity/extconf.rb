require 'mkmf'

WS_LIB_PATH = File.expand_path('../lib', __FILE__)
LIBDIR      = RbConfig::CONFIG['libdir']
INCLUDEDIR  = RbConfig::CONFIG['includedir']
HEADER_DIRS = [INCLUDEDIR]
LIB_DIRS    = [WS_LIB_PATH, LIBDIR]

extension_name = 'whitesimilarity'

dir_config(extension_name, HEADER_DIRS, LIB_DIRS)

unless have_header('lib/whitesimilarity.h')
  abort "Need 'lib/whitesimilarity.h'"
end

unless have_library('white_similarity', nil)
  abort "Need 'libwhite_similarity'"
end

create_makefile(extension_name)
