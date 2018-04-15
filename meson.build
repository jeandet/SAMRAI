project('SAMRAI', 'cpp' , 'fortran', default_options : ['cpp_std=c++11'], license : 'GPLv2',version:'3.11.1' , meson_version:'>=0.45.1')

m4 = find_program('m4')

if not meson.is_subproject()
    compiler_id = meson.get_compiler('cpp').get_id()

    if compiler_id == 'intel'
        add_global_link_arguments('-lifcore', language:'cpp')
    elif compiler_id == 'gcc'
        add_global_link_arguments('-lgfortran', language:'cpp')
    else
        error('Unsuported compiler')
    endif
endif

m4_generator = generator(m4,
			output  : '@BASENAME@.f',
			capture : true,
                	arguments : [
                	'-DPDAT_FORTDIR='+meson.current_source_dir()+'/source/SAMRAI/pdat/fortran',
                	'-DFORTDIR=@CURRENT_SOURCE_DIR@/fortran',
                	'@INPUT@'])


SAMRAI_glob_dep = []
if get_option('with-mpi')
    SAMRAI_glob_dep = [ dependency('mpi', language: 'cpp'), dependency('mpi', language: 'fortran')]
endif

subdir('source')
