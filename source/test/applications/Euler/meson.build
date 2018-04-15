euler_srcs = ['Euler.C', 'main.C']

euler__fortran_sources = m4_generator.process(
    ['fortran/avgint2d.m4',
     'fortran/avgint3d.m4',
     'fortran/flaten1d2d.m4',
     'fortran/flaten1d3d.m4',
     'fortran/flux2d.m4',
     'fortran/flux3d.m4',
     'fortran/fluxcorner3d.m4',
     'fortran/grad2d.m4',
     'fortran/grad3d.m4',
     'fortran/init2d.m4',
     'fortran/init3d.m4',
     'fortran/stable2d.m4',
     'fortran/stable3d.m4',
     'fortran/stufprobc.m4',
     'fortran/trace1d2d.m4',
     'fortran/trace1d3d.m4',
     'fortran/trace2d.m4',
     'fortran/trace3d.m4']
)

euler = executable('Euler', euler_srcs, euler__fortran_sources, link_args:['-lgfortran'], dependencies:[SAMRAI_tbox_dep, SAMRAI_xfer_dep, SAMRAI_algs_dep, SAMRAI_geom_dep, SAMRAI_appu_dep])
