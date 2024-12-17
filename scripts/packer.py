
import os
import sys
import subprocess

def find_valid_directories_with_cmake(directory: str):
    valid_dirs = []

    for entry in os.listdir(directory):
        full_path = os.path.join(directory, entry)

        if os.path.isdir(full_path):
            cmake_file_path = os.path.join(full_path, 'CMakeCache.txt')

            if os.path.isfile(cmake_file_path):
                valid_dirs.append(full_path)

    return valid_dirs


def cmake_build_dir(directory: str, target: str):
    thread_count = os.cpu_count()
    command = f"cmake --build {directory} --target {target} -j {thread_count}"

    print(f"\n\n[Build]: {command}\n\n")
    result = subprocess.run(command, capture_output=True, text=True)

    print(result.stdout)
    print('\n')
    if result.stderr:
        print("\n[Error]:\n")
        print(result.stderr)

    return result.returncode


def build_all_configuration(target_dir: str, target: str):
    valid_dirs = find_valid_directories_with_cmake(target_dir)

    success = 0
    for directory in valid_dirs:
        return_code = cmake_build_dir(directory, target)
        if return_code == 0:
            success += 1

    total = len(valid_dirs)
    print(f"\n\n[AllFinished]: total: {total} success: {success}\n\n")

    pass


def main():
    target_dir = os.path.abspath(sys.argv[1])
    target = sys.argv[2]
    print(f"target dir: {target_dir}")
    print(f"target: {target}")
    build_all_configuration(target_dir, target)
    pass


if __name__ == "__main__":
    main()

