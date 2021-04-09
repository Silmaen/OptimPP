pipeline {
    agent any
    stages {
        stage('clean'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g clear
            }
        }
        stage('generate'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g generate
            }
        }
        stage('build'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g build
            }
        }
        stage('test'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g test
            }
        }
        stage('doc'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g doc
            }
        }
        stage('package'){
            steps {
                python ./tools/BuildEngine.py -c gcc -g package
            }
        }
    }
}