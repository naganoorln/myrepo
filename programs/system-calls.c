System calls:
Deep Dive: How write () System Call Works (Step by Step)

The write () system call allows a user-space process to write data to a file descriptor (FD). Here’s a detailed breakdown of what happens at each step, from user space to kernel space and back.
Overview of the Execution Path
User Space → Kernel Space → System Call Table → sys_write() → File System → Kernel Space → User Space

1.Step-by-Step Execution	
User-Space Function Call:
A user-space program calls write (), which is provided by the C standard library (Glibc).
Example: write (fd, "Hello", 5);
The function does not directly interact with the kernel. Instead, it calls a wrapper function in Glibc.

2.glibc Wrapper Function Calls syscall:
#include <unistd.h>
#include <sys/syscall.h>
ssize_t write(int fd, const void *buf, size_t count) 
{
    return syscall(SYS_write, fd, buf, count);
}

The glibc function prepares registers before calling the actual syscall instruction.
Registers used for system calls on x86-64 architecture: 
Rax -- System call number (1 for write ()) 
rdi -- File descriptor (fd) 
rsi -- Pointer to buffer ("Hello") 
rdx -- Number of bytes to write (5) 

The wrapper function:
mov rax, 1          # Syscall number for sys_write
mov rdi, fd         # First argument: file descriptor
mov rsi, buffer     # Second argument: pointer to data
mov rdx, size       # Third argument: number of bytes
syscall             # Invoke kernel mode

3.CPU Executes syscall Instruction
CPU switches from user mode (Ring 3) → kernel mode (Ring 0).
The CPU reads the MSR_LSTAR register, which holds the address of entry_SYSCALL_64().
Control jumps to entry_SYSCALL_64() (defined in arch/x86/entry/entry_64.S).

4.Kernel Entry Point: entry_SYSCALL_64()
The kernel saves user-space register states onto the kernel stack.
Switches stack from the user-space stack to the kernel-space stack.
Calls do_syscall_64(), passing the system call number (rax) and arguments (rdi, rsi, rdx).
entry_SYSCALL_64:
swapgs                      # Switch to kernel stack
movq %rsp, %rdi             # Save user stack pointer
movq PER_CPU_VAR(cpu_current_top_of_stack), %rsp  # Switch to kernel stack
call do_syscall_64          # Call main syscall dispatcher

5.do_syscall_64(): Dispatching the System Call
This function reads the system call number from rax.
It looks up the corresponding function pointer in the system call table (sys_call_table[]).
The write() syscall corresponds to sys_write() in the kernel.

static long do_syscall_64(struct pt_regs *regs) 
{
long syscall_num = regs->rax;        // Get system call number
    	sys_call_t *func = sys_call_table[syscall_num];  // Lookup function
    	return func(regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9);
}

6.sys_write() Execution (Inside the Kernel)
The kernel validates parameters (e.g., checks if the file descriptor is valid).
Calls vfs_write() to interact with the virtual file system (VFS).

SYSCALL_DEFINE3(write, unsigned int, fd, const char __user *, buf, size_t, count) 
{
    struct file *file;
   	ssize_t ret;
    file = fget(fd);  // Get the file struct from fd
    if (!file)
    	return -EBADF;
    ret = vfs_write(file, buf, count, &file->f_pos);  // Call VFS layer
    fput(file);
    return ret;
}

7.Virtual File System (VFS) Layer
vfs_write() determines which file system (ext4, NFS, etc.) is being used.
It calls the specific file system's write function (e.g., ext4_file_write() for an ext4 file).

ssize_t vfs_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) 
{
    return file->f_op->write(file, buf, count, pos);
}

8.File System Driver Writes Data
Example: If writing to an ext4 file, the function ext4_file_write_iter() is executed.
The driver interacts with the block device driver to store the data on disk.
Return Path: Kernel to User Space
After writing, sys_write() returns the number of bytes written.
The return value is stored in rax.
do_syscall_64() restores registers and calls sysretq, switching back to user mode.
sysretq    # Return to user space
User Process Resumes Execution
The user process receives the return value in rax.
It checks if writing was successful and continues execution.

ssize_t bytes_written = write(fd, "Hello", 5);
if (bytes_written < 0) 
{
    perror("write failed");
}

✅ System calls switch execution from user mode (Ring 3) to kernel mode (Ring 0).
✅ Registers hold syscall numbers and arguments, set up by glibc before calling syscall.
✅ The syscall handler (do_syscall_64()) looks up the function in sys_call_table[].
✅ sys_write() calls vfs_write(), which interacts with the appropriate file system.
✅ The kernel returns the result via rax, and the process continues in user mode.

System Call Table and How New Syscalls Are Added to the Kernel

The system call table (sys_call_table[]) is a critical data structure in the Linux kernel. It maps system call numbers to their corresponding kernel functions.
When a system call is executed (syscall instruction), the kernel:
•	Reads the system call number from rax
•	Looks up the corresponding function in sys_call_table[]
•	Calls the function with arguments stored in registers

System Call Table (sys_call_table[])
The system call table is an array of function pointers, defined in:
File: arch/x86/entry/syscalls/syscall_64.tbl

Example (syscall_64.tbl for x86-64 architecture):
0   common  sys_read
1   common  sys_write
2   common  sys_open
3   common  sys_close
Here, sys_write is assigned syscall number 1.
System Call Lookup and Execution
do_syscall_64() Retrieves the Function
File: arch/x86/entry/common.c

static long do_syscall_64(struct pt_regs *regs) 
{
    long syscall_num = regs->rax;        // Get system call number
    sys_call_t *func = sys_call_table[syscall_num];  // Lookup function
    return func(regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9);
}
The syscall function pointer (sys_write) is called dynamically.

How to Add a New System Call to the Linux Kernel
If you want to add a custom system call sys_hello(), follow these steps:
Implement the New System Call
File: kernel/sys_hello.c
#include <linux/kernel.h>
#include <linux/syscalls.h>
SYSCALL_DEFINE0(hello) 
{
    printk(KERN_INFO "Hello, Kernel!\n");
    return 0;
}
SYSCALL_DEFINE0 means no arguments.
Register the Syscall in the Table
File: arch/x86/entry/syscalls/syscall_64.tbl
450 common  sys_hello
Syscall number 450 is assigned.

 
Declare the Syscall in Kernel Header
File: include/linux/syscalls.h
asmlinkage long sys_hello(void);
This makes the function visible to the kernel.
 
Compile and Boot the Kernel
After modifying the kernel:
make -j$(nproc)
make modules_install
make install
reboot

The system call is now available in the kernel.
Use the New Syscall in User Space
User program (test_hello.c)
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#define SYS_hello 450  // Our new syscall number
int main() 
{
    syscall(SYS_hello);
    return 0;
}
syscall(450) invokes sys_hello().
sys_call_table[] maps syscall numbers to functions.
New syscalls are added in syscall_64.tbl and syscalls.h. 
After recompiling the kernel, user programs can use syscall() to invoke the new syscall.

