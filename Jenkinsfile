#!/usr/bin/env groovy
pipeline {
    parameters {
        choice(name: 'PLATFORM_FILTER', choices: ['all', 'linux', 'windows'], description: 'Run on specific platform')
    }
    agent none
    stages {
        stage('Static analysis') {
            agent any
            steps {
                echo "Static code analysis ${env.BRANCH_NAME }"
            }
        }
        stage('Documentation') {
            agent any
            steps {
                echo "Documentation generation"
            }
        }
        stage('generate build test') {
            matrix {
                agent {
                    label "${PLATFORM}"
                }
                when { anyOf {
                    expression { params.PLATFORM_FILTER == 'all' }
                    expression { params.PLATFORM_FILTER == env.PLATFORM }
                } }
                // axis of the matrix
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'linux', 'windows'
                    }
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang', 'clang-native', 'msvc'
                    }
                    axis {
                        name 'CONFIGURATION'
                        values 'release', 'debug'
                    }
                }
                // exclusions
                excludes {
                    exclude {
                        // clang-cl and msvc only exists on windows!
                        axis {
                            name 'PLATFORM'
                            notValues 'windows'
                        }
                        axis {
                            name 'COMPILER'
                            values 'clang-native', 'msvc'
                        }
                    }
                }
                stages {
                    stage('build') {
                        steps {
                            script {
                                if (${CONFIGURATION} == "debug")
                                    arg = " -g"
                                else
                                    arg = ""
                            }
                            echo "Do generate for ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                            sh 'python Tools/BuildEngine.py -c ${COMPILER} ${arg} generate'
                            echo "Do build ${PLATFORM} - ${COMPILER}- ${CONFIGURATION}"
                            sh 'python Tools/BuildEngine.py -c ${COMPILER} ${arg} build'
                        }
                    }
                    stage('test') {
                        steps {
                            echo "Do test ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                            sh 'python Tools/BuildEngine.py -c ${COMPILER} ${arg} test'
                        }
                    }
                    stage('packing') {
                        steps {
                            echo "Do packing ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                            sh 'python Tools/BuildEngine.py -c ${COMPILER} ${arg} package'
                        }
                    }
                }

                post {
                    always {
                        archiveArtifacts artifacts: 'cmake-build-${CONFIGURATION}-${COMPILER}/*.zip', fingerprint: true
                        junit 'cmake-build-${CONFIGURATION}-${COMPILER}/Test/*.xml'
                    }
                }
            }
        }
    }
}