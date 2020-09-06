algs_sources_C = ['TimeRefinementIntegrator.C',
	'TimeRefinementIntegratorConnectorWidthRequestor.C',
	'TimeRefinementLevelStrategy.C',
	'HyperbolicPatchStrategy.C',
	'HyperbolicLevelIntegrator.C',
	'ImplicitEquationStrategy.C',
	'ImplicitIntegrator.C',
	'MethodOfLinesIntegrator.C',
	'MethodOfLinesPatchStrategy.C',
	'OuternodeSumTransaction.C',
	'OuternodeSumTransactionFactory.C',
	'PatchBoundaryNodeSum.C',
	'OuteredgeSumTransaction.C',
	'OuteredgeSumTransactionFactory.C',
	'PatchBoundaryEdgeSum.C']

algs_headers = ['HyperbolicLevelIntegrator.h',
 'HyperbolicPatchStrategy.h',
 'ImplicitEquationStrategy.h',
 'ImplicitIntegrator.h',
 'MethodOfLinesIntegrator.h',
 'MethodOfLinesPatchStrategy.h',
 'OuteredgeSumTransaction.h',
 'OuteredgeSumTransactionFactory.h',
 'OuternodeSumTransaction.h',
 'OuternodeSumTransactionFactory.h',
 'PatchBoundaryEdgeSum.h',
 'PatchBoundaryNodeSum.h',
 'TimeRefinementIntegrator.h',
 'TimeRefinementIntegratorConnectorWidthRequestor.h',
 'TimeRefinementLevelStrategy.h']


algs_fortran_sources = m4_generator.process(
	[
	 'fortran/algs_nodeouternodeops2d.m4',
	 'fortran/algs_nodeouternodeops3d.m4',
	 'fortran/algs_upfluxsum1d.m4',
	 'fortran/algs_upfluxsum2d.m4',
	 'fortran/algs_upfluxsum3d.m4'
	 ]
)

algs_sources = C_to_cpp_gen.process(algs_sources_C)

algs = library('SAMRAI_algs', sources:[algs_fortran_sources, algs_sources],
	include_directories:SAMRAI_inc,
	dependencies:[SAMRAI_mesh_dep, SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_glob_dep]
	)

SAMRAI_algs_dep = declare_dependency(include_directories:SAMRAI_inc, link_with:algs,
	dependencies:[SAMRAI_mesh_dep, SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_glob_dep])
