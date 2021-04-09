pipeline {
    agent any
    stages {
        stage("clean"){
            steps {
                echo "Clearing the repository builds"
                sh "python Tools/BuildEngine.py -c gcc -g clear"
            }
        }
        stage("generate"){
            steps {
                echo "Generating configuration for Debug Gcc"
                sh "python Tools/BuildEngine.py -c gcc -g generate"
            }
        }
        stage("build"){
            steps {
                echo "Build"
                sh "python Tools/BuildEngine.py -c gcc -g build"
            }
        }
        stage("test"){
            steps {
                echo "Testing the build"
                sh "python Tools/BuildEngine.py -c gcc -g test"
            }
        }
        stage("documentation"){
            steps {
                echo "Generate the documentation"
                sh "python Tools/BuildEngine.py -c gcc -g doc"
            }
        }
        stage("package"){
            steps {
                echo "Packaging the artifact"
                sh "python Tools/BuildEngine.py -c gcc -g package"
            }
        }
    }
}