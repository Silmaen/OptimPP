#!/usr/bin/env groovy
pipeline {
    agent any


    stages {
        parallel {
            stage("linux gcc Debug") {
                agent { node { label "Linux" } }
                stage("clean"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g clear"
                    }
                }
                stage("generate"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g generate"
                    }
                }
                stage("build"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g build"
                    }
                }
                stage("test"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g test"
                    }
                }
                stage("documentation"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g doc"
                    }
                }
                stage("package"){
                    steps {
                        sh "python Tools/BuildEngine.py -c gcc -g package"
                    }
                }
            }
            stage("linux clang Debug") {
                agent { node { label "Linux" } }
                stage("clean"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g clear"
                    }
                }
                stage("generate"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g generate"
                    }
                }
                stage("build"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g build"
                    }
                }
                stage("test"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g test"
                    }
                }
                stage("documentation"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g doc"
                    }
                }
                stage("package"){
                    steps {
                        sh "python Tools/BuildEngine.py -c clang -g package"
                    }
                }
            }
        }
    }
}