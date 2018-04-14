xfer_sources = ['BoxGeometryVariableFillPattern.C',
	'PatchInteriorVariableFillPattern.C',
	'PatchLevelFullFillPattern.C',
	'PatchLevelBorderFillPattern.C',
	'PatchLevelBorderAndInteriorFillPattern.C',
	'PatchLevelEnhancedFillPattern.C',
	'PatchLevelInteriorFillPattern.C',
	'PatchLevelFillPattern.C',
	'VariableFillPattern.C',
	'RefineAlgorithm.C',
	'CoarsenAlgorithm.C',
	'RefineSchedule.C',
	'RefineScheduleConnectorWidthRequestor.C',
	'CoarsenSchedule.C',
	'RefineTimeTransaction.C',
	'RefineCopyTransaction.C',
	'StandardRefineTransactionFactory.C',
	'RefineTransactionFactory.C',
	'RefinePatchStrategy.C',
	'RefineClasses.C',
	'CoarsenCopyTransaction.C',
	'StandardCoarsenTransactionFactory.C',
	'CoarsenTransactionFactory.C',
	'CoarsenPatchStrategy.C',
	'CoarsenClasses.C',
	'SingularityPatchStrategy.C',
	'CompositeBoundaryAlgorithm.C',
	'CompositeBoundarySchedule.C']


xfer_headers = ['BoxGeometryVariableFillPattern.h',
 'CoarsenAlgorithm.h',
 'CoarsenClasses.h',
 'CoarsenCopyTransaction.h',
 'CoarsenPatchStrategy.h',
 'CoarsenSchedule.h',
 'CoarsenTransactionFactory.h',
 'CompositeBoundaryAlgorithm.h',
 'CompositeBoundarySchedule.h',
 'PatchInteriorVariableFillPattern.h',
 'PatchLevelBorderAndInteriorFillPattern.h',
 'PatchLevelBorderFillPattern.h',
 'PatchLevelEnhancedFillPattern.h',
 'PatchLevelFillPattern.h',
 'PatchLevelFullFillPattern.h',
 'PatchLevelInteriorFillPattern.h',
 'RefineAlgorithm.h',
 'RefineClasses.h',
 'RefineCopyTransaction.h',
 'RefinePatchStrategy.h',
 'RefineSchedule.h',
 'RefineScheduleConnectorWidthRequestor.h',
 'RefineTimeTransaction.h',
 'RefineTransactionFactory.h',
 'SingularityPatchStrategy.h',
 'StandardCoarsenTransactionFactory.h',
 'StandardRefineTransactionFactory.h',
 'VariableFillPattern.h']




xfer = library('SAMRAI_xfer', sources:[xfer_sources],
	include_directories:SAMRAI_inc,
	dependencies:[SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep]
	)


SAMRAI_xfer_dep = declare_dependency(link_with:xfer, dependencies:[SAMRAI_tbox_dep, SAMRAI_hier_dep, SAMRAI_glob_dep])