pipeline {
    agent any

    options {
        timestamps()
    }

    environment {
        PATH = "C:\\MinGW\\bin;C:\\Users\\Ashwini S\\AppData\\Roaming\\Python\\Python39\\Scripts;${env.PATH}"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Verify Tools') {
            steps {
                bat '''
                echo ===== VERIFY TOOLS =====

                where g++
                g++ --version

                where gcc
                gcc --version

                where cmake
                cmake --version

                where conan
                conan --version
                '''
            }
        }

        stage('Clean') {
            steps {
                bat '''
                if exist build rmdir /s /q build
                mkdir build
                '''
            }
        }

        stage('Conan Install') {
            steps {
                bat '''
                cd build

                conan profile detect --force

                conan install .. ^
                    --output-folder=. ^
                    --build=missing
                '''
            }
        }

        stage('Configure') {
            steps {
                bat '''
                cd build

                cmake ^
                  -G "MinGW Makefiles" ^
                  -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ^
                  ..
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                cd build
                cmake --build .
                '''
            }
        }

        stage('Test') {
            steps {
                bat '''
                cd build
                ctest --output-on-failure
                '''
            }
        }

        stage('Run') {
            steps {
                bat '''
                cd build
                calculator_app.exe
                '''
            }
        }

        stage('Package') {
            steps {
                bat '''
                if not exist artifacts mkdir artifacts
                copy build\\calculator_app.exe artifacts\\
                '''
            }
        }

        stage('Archive') {
            steps {
                archiveArtifacts artifacts: 'artifacts/*', fingerprint: true
            }
        }
    }

    post {
        always {
            echo "Pipeline Finished"
        }

        success {
            echo "BUILD SUCCESSFUL"
        }

        failure {
            echo "BUILD FAILED"
        }
    }
}