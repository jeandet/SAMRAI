
 cpp_compiler = meson.get_compiler('cpp')
 conf_data = configuration_data()
 if cpp_compiler.has_header('iomanip')
 	conf_data.set('IOMANIP_HEADER_FILE', '<iomanip>') # should add this as an option
 endif
 conf_data.set('SAMRAI_MAXIMUM_DIMENSION', 3) # should add this as an option

 configure_file(input : '../../config/SAMRAI_config.h.meson.in',
                output : 'SAMRAI_config.h',
                configuration : conf_data)

subdir('tbox')
subdir('hier')
subdir('xfer')
subdir('pdat')
subdir('mesh')
subdir('algs')
subdir('math')
subdir('geom')
subdir('appu')
subdir('solv')

