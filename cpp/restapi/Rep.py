import subprocess, json, os, shlex

# TODO: vpfs_actions or vpfsadm are called in the context of
# subprocess.check_output which is inefficient. Devise a better
# apporach (python binding or sharedlib or some thing else).

def configRep(user, passwd, targetHost):
    cmd = "/root/setup_vpfsrep_target.sh --login=" + user + " --passwd=" + passwd + " --targethost=" + targetHost
    args = shlex.split(cmd)
    status = subprocess.check_output(args)
    return status

def startReplicationJob(sourceImg, targetImg, targetHost, mountPoint):
    repParams  = {'sourceImageId':sourceImg,
                  'targetImageId':targetImg,
                  'targetHost':targetHost}
    optdup_json_file = "/tmp/optdup_tmp.json"
    with open(optdup_json_file, 'w') as tmpoutfile:
        json.dump(repParams, tmpoutfile)
    cmd = "/usr/openv/pdde/vpfs/bin/vpfsadm --startOptdup " + optdup_json_file + " --mountPoint " + mountPoint
    args = shlex.split(cmd)
    status = subprocess.check_output(args)
    return (status)
