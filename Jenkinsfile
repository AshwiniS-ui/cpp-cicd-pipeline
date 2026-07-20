pipeline {
    agent any

    options {
        timestamps()
    }

    stages {

        stage('Checkout') {
            steps {
                echo "Checking out source code from GitHub..."
                checkout scm
            }
        }

        stage('Verify Tools') {
            steps {
                bat '''
                echo ===============================
                echo VERIFYING BUILD TOOLS
                echo ===============================

                git --version
                cmake --version
                g++ --version

                echo.
                echo Git Location
                where git

                echo.
                echo GCC Location
                where g++

                echo.
                echo CMake Location
                where cmake
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
        if exist build (
            rmdir /s /q build
        )

        mkdir build

        cd build

        conan profile detect --force

        conan install .. --output-folder=. --build=missing

        cmake -G "MinGW Makefiles" ^
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
stage('Unit Tests') {
    steps {
        bat '''
        cd build

        ctest --output-on-failure
        '''
    }
}

        stage('Run Application') {
            steps {
                bat '''
                echo ===============================
                echo RUNNING APPLICATION
                echo ===============================

                cd build

                calculator_app.exe
                '''
            }
        }

        stage('Package') {
            steps {
                bat '''
                echo ===============================
                echo PACKAGING APPLICATION
                echo ===============================

                if not exist artifacts (
                    mkdir artifacts
                )

                copy build\\calculator_app.exe artifacts\\
                '''
            }
        }
        
}
    }

    post {

        success {
            echo "========================================="
            echo "BUILD SUCCESSFUL"
            echo "========================================="
        }

        failure {
            echo "========================================="
            echo "BUILD FAILED"
            echo "========================================="
        }

        always {
            echo "Pipeline Finished."
        }
    }
