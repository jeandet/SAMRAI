conv_diff_srcs = ['ConvDiff.C', 'MainRestartData.C', 'main.C']

conv_diff__fortran_sources = m4_generator.process(
    ['fortran/compute_rhs2d.m4',
     'fortran/compute_rhs3d.m4',
     'fortran/init2d.m4',
     'fortran/init3d.m4',
     'fortran/rkstep2d.m4',
     'fortran/rkstep3d.m4',
     'fortran/tag_cells2d.m4',
     'fortran/tag_cells3d.m4']
)

conv_diff = executable('ConvDiff', conv_diff_srcs, conv_diff__fortran_sources, dependencies:[SAMRAI_tbox_dep, SAMRAI_algs_dep, SAMRAI_geom_dep, SAMRAI_appu_dep])
