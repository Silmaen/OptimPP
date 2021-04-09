#!/usr/bin/env groovy
pipeline {
    agent none
    stages {
        stage('generate build test') {
            matrix {
                agent any
                // axis of the matrix
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'OpenBSD', 'Linux', 'Windows'
                    }
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang', 'clang-native', 'msvc'
                    }
                    axis {
                        name 'CONFIGURATION'
                        values 'Release', 'Debug'
                    }
                }
                // exclusions
                excludes {
                    exclude {
                        // clang-cl and msvc only exists on windows!
                        axis {
                            name 'PLATFORM'
                            notValues 'Windows'
                        }
                        axis {
                            name 'COMPILER'
                            values 'clang-native', 'msvc'
                        }
                    }
                }
                stages {
                    stage('generate') {
                        steps {
                            echo "Do generate for ${PLATFORM} - ${CONFIGURATION}"
                        }
                    }
                    stage('build') {
                        steps {
                            echo "Do build ${PLATFORM} - ${CONFIGURATION}"
                        }
                    }

                    stage('test') {
                        steps {
                            echo "Do test ${PLATFORM} - ${CONFIGURATION}"
                        }
                    }
                }
            }
        }
        stage('Documentation') {
            agent any
            steps {
                echo "Documentation generation"
            }
        }
    }
}