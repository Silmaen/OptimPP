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
                        values 'gcc', 'clang', 'clang-native', 'visual-studio'
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
                            values 'clang-native', 'visual-studio'
                        }
                    }
                }
                stages {
                    stage('build') {
                        steps {
                            script {
                                echo "Do generate for ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (isUnix()) {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -f ${CONFIGURATION} generate build'
                                } else {
                                    bat 'python Tools/BuildEngine.py -c %COMPILER% -f %CONFIGURATION% generate build'
                                }
                            }
                        }
                    }
                    stage('test') {
                        steps {
                            script {
                                echo "Do test ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (isUnix()) {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -f ${CONFIGURATION} test'
                                } else  {
                                    bat 'python Tools/BuildEngine.py -c %COMPILER% -f %CONFIGURATION%  test'
                                }
                            }
                        }
                    }
                    stage('packing') {
                        steps {
                            script {
                                echo "Do packing ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                                if (isUnix()) {
                                    sh 'python Tools/BuildEngine.py -c ${COMPILER} -f ${CONFIGURATION} package'
                                } else  {
                                    bat 'python Tools/BuildEngine.py -c %COMPILER% -f %CONFIGURATION% package'
                                }
                            }
                        }
                    }
                }

                post {
                    always {
                        archiveArtifacts artifacts: 'cmake-build-*-*/*.zip', fingerprint: true
                        xunit([GoogleTest(pattern: 'cmake-build-*-*/Test/*.xml', stopProcessingIfError: true)])
                    }
                }
            }
        }
    }
}