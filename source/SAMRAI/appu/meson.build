appu_sources = ['BoundaryUtilityStrategy.C',
	'VisItDataWriter.C',
	'VisDerivedDataStrategy.C',
	'VisMaterialsDataStrategy.C',
	'CartesianBoundaryUtilities2.C',
	'CartesianBoundaryUtilities3.C']


appu_headers = ['BoundaryUtilityStrategy.h',
 'CartesianBoundaryDefines.h',
 'CartesianBoundaryUtilities2.h',
 'CartesianBoundaryUtilities3.h',
 'VisDerivedDataStrategy.h',
 'VisItDataWriter.h',
 'VisMaterialsDataStrategy.h']


appu_fortran_sources = m4_generator.process(
	['fortran/appu_cartbdry2d.m4', 'fortran/appu_cartbdry3d.m4']
)

appu = library('SAMRAI_appu', sources:[appu_fortran_sources, appu_sources],
	include_directories:SAMRAI_inc,
	dependencies: [SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_glob_dep],
	link_args:['-lgfortran']
	)

SAMRAI_appu_dep = declare_dependency(link_with:appu,
	dependencies: [SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_glob_dep])