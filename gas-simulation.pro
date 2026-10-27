# Builds both programs: text/gas_text (terminal) and gl/gas_gl (3D view).
# Usage: qmake && make

TEMPLATE = subdirs

SUBDIRS += \
    text \
    gl
