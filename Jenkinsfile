def artifactory_name = "artifactory_local"
def artifactory_repo = "conan-local"
String docker_image = "conanio/gcc8"

node {
    docker.image(docker_image).inside('-v /tmp/:/tmp/ --net=host') {
        //def server = Artifactory.server artifactory_name
        def client = Artifactory.newConanClient()
        //def serverName = client.remote.add server: server, repo: artifactory_repo

        stage("Get project") {
              checkout scm
        }

        stage("Get dependencies and create app") {
            client.run(command: "remote remove conan-center" )
            String createCommand = "create . sword/sorcery --profile /home/conan/.conan/profiles/default"
            client.run(command: createCommand)
        }

        stage("Upload packages") {
            String uploadCommand = "upload ui-tileset* --all -r ${serverName} --confirm"
            def b = client.run(command: command)
            b.env.collect()
            server.publishBuildInfo b
        }
    }
}
