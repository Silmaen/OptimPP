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
                                echo "Do generate for ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (CONFIGURATION == "debug") {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -g generate'
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -g build'
                                } else  {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER}  generate'
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER}  build'
                                }
                            }
                        }
                    }
                    stage('test') {
                        steps {
                            script {
                                echo "Do test ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (CONFIGURATION == "debug") {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -g test'
                                } else  {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER}  test'
                                }
                            }
                        }
                    }
                    stage('packing') {
                        steps {
                            script {
                                echo "Do packing ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (CONFIGURATION == "debug") {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -g package'
                                } else  {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER}  package'
                                }
                            }
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