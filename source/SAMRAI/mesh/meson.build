mesh_sources_C = ['BoxTransitSet.C',
 'GriddingAlgorithmStrategy.C',
 'BergerRigoutsos.C',
 'BergerRigoutsosNode.C',
 'TagAndInitializeStrategy.C',
 'SpatialKey.C',
 'StandardTagAndInitializeConnectorWidthRequestor.C',
 'CascadePartitioner.C',
 'BalanceUtilities.C',
 'StandardTagAndInitStrategy.C',
 'GriddingAlgorithm.C',
 'BoxGeneratorStrategy.C',
 'BalanceBoxBreaker.C',
 'PartitioningParams.C',
 'TreeLoadBalancer.C',
 'CascadePartitionerTree.C',
 'TransitLoad.C',
 'LoadBalanceStrategy.C',
 'VoucherTransitLoad.C',
 'MultiblockGriddingTagger.C',
 'GriddingAlgorithmConnectorWidthRequestor.C',
 'ChopAndPackLoadBalancer.C',
 'TileClustering.C',
 'StandardTagAndInitialize.C']


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

mesh_sources = C_to_cpp_gen.process(mesh_sources_C)

mesh = library('SAMRAI_mesh', sources:[mesh_fortran_sources, mesh_sources],
	include_directories:SAMRAI_inc,
	dependencies: [SAMRAI_pdat_dep, SAMRAI_xfer_dep, SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep]
	)

SAMRAI_mesh_dep = declare_dependency(link_with:mesh,
	dependencies: [SAMRAI_pdat_dep, SAMRAI_xfer_dep, SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep])
