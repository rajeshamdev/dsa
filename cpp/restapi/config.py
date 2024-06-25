import subprocess, os, shlex

# TODO: vpfs_actions or vpfsadm are called in the context of
# subprocess.check_output which is inefficient. Devise a better
# apporach (python binding or sharedlib or some thing else).

def createAndExportShare(imageId, clientHost):
    print imageId, clientHost
    cmd = "/usr/openv/pdde/vpfs/bin/vpfs_actions  --action createAndExport --imageId " + imageId + " --clientHost " + clientHost
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

def snapshotAndExport(sourceImageId, destinationImageId, clientHost):
    cmd = "/usr/openv/pdde/vpfs/bin/vpfs_actions  --action snapshotAndExport --sourceImageId " \
            + sourceImageId + " --destinationImageId " + destinationImageId + " --clientHost " + clientHost
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

def mountShare(imageId):
    cmd = "/usr/openv/pdde/vpfs/bin/vpfs_actions --action mount --imageId " + imageId
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

def unExportAndDeleteShare(mountPoint, clientHost):
    print mountPoint, clientHost
    cmd = "/usr/openv/pdde/vpfs/bin/vpfs_actions  --action unexportAndDelete --mountPoint " + mountPoint + " --clientHost " + clientHost
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

def unmount(mountPoint):
    cmd = "/usr/openv/pdde/vpfs/bin/vpfsadm --umount --mountPoint " + mountPoint
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

def deleteShare(imageId):
    cmd = "/usr/openv/pdde/vpfs/bin/vpfs_actions --action delete --imageId " + imageId
    args = shlex.split(cmd)
    args = shlex.split(cmd)
    retmsg = subprocess.check_output(args)
    return retmsg

