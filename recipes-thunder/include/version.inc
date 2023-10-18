# Gets the branch name from version number
def GetMajorVersion(v):
    return v.split('.')[0]

def GetMinorVersion(v):
    return v.split('.')[1]

RECIPE_BRANCH ?= "R${@GetMajorVersion('${PV}')}_${@GetMinorVersion('${PV}')}"

RECIPE_TAG ?= "R${PV}"
