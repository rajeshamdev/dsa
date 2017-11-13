from flask import Flask
from flask import jsonify
from flask import request

import vpfsConfigApi as vpfsConfig
import vpfsRepApi as vpfsRep

vpfsapp = Flask(__name__)

@vpfsapp.route('/config', methods=['POST'])
def config():
    opType = request.json['opType']
    if opType == 'createAndExport' :
        imageId    = request.json['imageId']
        clientHost = request.json['clientHost']
        status     = vpfsConfig.createAndExportShare(imageId, clientHost)
        return jsonify({'configOpts' : status})
    elif opType == 'unexportAndDelete' :
        mountPoint = request.json['mountPoint']
        clientHost = request.json['clientHost']
        status     = vpfsConfig.unExportAndDeleteShare(mountPoint, clientHost)
        return jsonify({'configOpts' : status})
    elif opType == 'snapshotAndExport':
        sourceImageId      = request.json['sourceImageId']
        destinationImageId = request.json['destinationImageId']
        clientHost         = request.json['clientHost']
        status = vpfsConfig.snapshotAndExport(sourceImageId, destinationImageId, clientHost)
        return jsonify({'configOpts' : status})
    elif opType == 'umount':
        mountPoint = request.json['mountPoint']
        status     = vpfsConfig.unmount(mountPoint)
        return jsonify({'configOpts' : status})
    elif opType == 'configRep':
        user       = request.json['user']
        passwd     = request.json['passwd']
        targetHost = request.json['targetHost']
        status     = vpfsRep.configRep(user, passwd, targetHost)
        return jsonify({'configOpts' : status})

@vpfsapp.route('/vpfsrep', methods=['POST'])
def vpfsrep():
    opType = request.json['opType']
    if opType == 'startRepJob':
        sourceImg  = request.json['sourceImageId']
        targetImg  = request.json['targetImageId']
        targetHost = request.json['targetHost']
        mountPoint = request.json['mountPoint']
        status = vpfsRep.startReplicationJob(sourceImg, targetImg, targetHost, mountPoint)
        return jsonify({'Status' : status})
    elif opType == 'statusRepJob':
        print "TBD"
    elif opType == 'query':
        print "TBD"
    elif opType == 'cancelRepJob':
        print "TBD"

# Enable below code when vpfsapp is run in flask server (just for testing, not for deployment).
# export FLASK_APP=vpfsapp.py; flask run;
#
#if __name__ == '_
