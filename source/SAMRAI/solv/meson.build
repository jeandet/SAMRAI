solv_sources = ['PoissonSpecifications.C',
	'SNESAbstractFunctions.C',
	'CVODEAbstractFunctions.C',
	'CVODESolver.C',
	'KINSOLAbstractFunctions.C',
	'KINSOLSolver.C',
	'solv_NVector.C',
	'SundialsAbstractVector.C',
	'FACOperatorStrategy.C',
	'FACPreconditioner.C',
	'NonlinearSolverStrategy.C',
	'SNES_SAMRAIContext.C',
	'KINSOL_SAMRAIContext.C',
	'CartesianRobinBcHelper.C',
	'CellPoissonFACOps.C',
	'CellPoissonFACSolver.C',
	'CellPoissonHypreSolver.C',
	'GhostCellRobinBcCoefs.C',
	'LocationIndexRobinBcCoefs.C',
	'RobinBcCoefStrategy.C',
	'SimpleCellRobinBcCoefs.C',
	'Sundials_SAMRAIVector.C']


solv_headers = ['CVODEAbstractFunctions.h',
 'CVODESolver.h',
 'CartesianRobinBcHelper.h',
 'CellPoissonFACOps.h',
 'CellPoissonFACSolver.h',
 'CellPoissonHypreSolver.h',
 'FACOperatorStrategy.h',
 'FACPreconditioner.h',
 'GhostCellRobinBcCoefs.h',
 'KINSOLAbstractFunctions.h',
 'KINSOLSolver.h',
 'KINSOL_SAMRAIContext.h',
 'LocationIndexRobinBcCoefs.h',
 'NonlinearSolverStrategy.h',
 'PETScAbstractVectorReal.h',
 'PETSc_SAMRAIVectorReal.h',
 'PoissonSpecifications.h',
 'RobinBcCoefStrategy.h',
 'SAMRAIVectorReal.h',
 'SNESAbstractFunctions.h',
 'SNES_SAMRAIContext.h',
 'SimpleCellRobinBcCoefs.h',
 'SundialsAbstractVector.h',
 'Sundials_SAMRAIVector.h',
 'nvector.h',
 'solv_NVector.h']


solv_fortran_sources =['fortran/solv_cartesianrobinbchelper2d.f',
 'fortran/solv_cartesianrobinbchelper3d.f',
 'fortran/solv_cellpoissonfacops2d.f',
 'fortran/solv_cellpoissonfacops3d.f',
 'fortran/solv_cellpoissonhypresolver2d.f',
 'fortran/solv_cellpoissonhypresolver3d.f']


solv = library('SAMRAI_solv', sources:[solv_fortran_sources, solv_sources],
	include_directories:SAMRAI_inc,
	dependencies: [SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_math_dep, SAMRAI_glob_dep],
	link_args:['-lgfortran']
	)

SAMRAI_solv_dep = declare_dependency(link_with:solv,
	dependencies: [SAMRAI_hier_dep, SAMRAI_pdat_dep, SAMRAI_math_dep, SAMRAI_glob_dep])