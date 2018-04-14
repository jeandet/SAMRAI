mesh_sources = ['SpatialKey.C',
	'BoxGeneratorStrategy.C',
	'GriddingAlgorithm.C',
	'GriddingAlgorithmConnectorWidthRequestor.C',
	'StandardTagAndInitStrategy.C',
	'StandardTagAndInitialize.C',
	'StandardTagAndInitializeConnectorWidthRequestor.C',
	'TagAndInitializeStrategy.C',
	'BalanceUtilities.C',
	'TreeLoadBalancer.C',
	'GraphLoadBalancer.C',
	'ChopAndPackLoadBalancer.C',
	'CascadePartitioner.C',
	'CascadePartitionerTree.C',
	'LoadBalanceStrategy.C',
	'BalanceBoxBreaker.C',
	'BoxTransitSet.C',
	'VoucherTransitLoad.C',
	'TransitLoad.C',
	'GriddingAlgorithmStrategy.C',
	'BergerRigoutsos.C',
	'BergerRigoutsosNode.C',
	'MultiblockGriddingTagger.C',
	'TileClustering.C',
	'PartitioningParams.C']


mesh_headers = ['BalanceBoxBreaker.h',
 'BalanceUtilities.h',
 'BergerRigoutsos.h',
 'BergerRigoutsosNode.h',
 'BoxGeneratorStrategy.h',
 'BoxInTransit.h',
 'BoxTransitSet.h',
 'CascadePartitioner.h',
 'CascadePartitionerTree.h',
 'ChopAndPackLoadBalancer.h',
 'GraphLoadBalancer.h',
 'GriddingAlgorithm.h',
 'GriddingAlgorithmConnectorWidthRequestor.h',
 'GriddingAlgorithmStrategy.h',
 'LoadBalanceStrategy.h',
 'MultiblockGriddingTagger.h',
 'PartitioningParams.h',
 'SpatialKey.h',
 'StandardTagAndInitStrategy.h',
 'StandardTagAndInitialize.h',
 'StandardTagAndInitializeConnectorWidthRequestor.h',
 'TagAndInitializeStrategy.h',
 'TileClustering.h',
 'TransitLoad.h',
 'TreeLoadBalancer.h',
 'VoucherTransitLoad.h']




mesh_fortran_sources = m4_generator.process(
['fortran/mesh_coarsentags1d.m4',
 'fortran/mesh_coarsentags2d.m4',
 'fortran/mesh_coarsentags3d.m4']
)

mesh = library('SAMRAI_mesh', sources:[mesh_fortran_sources, mesh_sources],
	include_directories:SAMRAI_inc,
	dependencies: [SAMRAI_pdat_dep, SAMRAI_xfer_dep, SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep],
	link_args:['-lgfortran']
	)

SAMRAI_mesh_dep = declare_dependency(link_with:mesh,
	dependencies: [SAMRAI_pdat_dep, SAMRAI_xfer_dep, SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep])