#!/usr/bin/env groovy
pipeline {
    parameters {
        choice(name: 'PLATFORM_FILTER', choices: ['all', 'linux', 'windows', 'openbsd'], description: 'Run on specific platform')
    }
    agent none
    stages {
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
                        values 'openbsd', 'linux', 'windows'
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
                    stage('build') {
                        steps {
                            echo "Do generate for ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
                            echo "Do build ${PLATFORM} - ${COMPILER}- ${CONFIGURATION}"
                        }
                    }
                    stage('test') {
                        steps {
                            echo "Do test ${PLATFORM} - ${COMPILER} - ${CONFIGURATION}"
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