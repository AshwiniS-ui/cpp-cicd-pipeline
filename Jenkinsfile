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
        echo ===== VERIFY =====

        echo.
        echo Python
        where python
        python --version

        echo.
        echo Conan
        where conan

        echo.
        python -c "import sys; print(sys.executable)"
        python -c "import site; print(site.getusersitepackages())"

        echo.
        python -m pip show conan

        echo.
        python -c "import conan; print(conan.__file__)"

        echo.
        conan --version

        echo.
        echo GCC
        where gcc
        gcc --version

        echo.
        echo G++
        where g++
        g++ --version
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
        }Archive') {
            ste

        stage('ps {
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