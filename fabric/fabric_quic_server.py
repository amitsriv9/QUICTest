from __future__ import with_statement
from fabric.api import local, run, abort, settings, cd
from fabric.contrib.console import confirm


#quic-b2.cs.wpi.edu
def host_type():
    local('uname -s')
    #run('uname -s')


def deploy():
    code_dir= '/home/aksrivastava/networkTest'
    with cd(code_dir):
       run("./quic_server --quic_in_memory_cache_dir=/quic-data/www.example.org --key_file=net/tools/quic/certs/out/leaf_cert.pkcs8 --certificate_file=net/tools/quic/certs/out/leaf_cert.pem &")
       run("./u_tcp_server 9850 2011-Aug02-MPCV-HIB-splash.mp4 &")
