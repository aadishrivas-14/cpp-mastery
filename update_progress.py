#!/usr/bin/env python3
"""
C++ Mastery Progress Updater
Usage: python3 update_progress.py [command] [args]
"""

import os
import sys
import json
from datetime import datetime

PROGRESS_FILE = "progress_state.json"
TRACKER_FILE = "PROGRESS_TRACKER.md"

def load_progress():
    """Load progress from JSON file"""
    if os.path.exists(PROGRESS_FILE):
        with open(PROGRESS_FILE, 'r') as f:
            return json.load(f)
    return {
        "current_week": 1,
        "current_day": 1,
        "completed_tasks": [],
        "completed_theory": [],
        "completed_projects": [],
        "scores": {"week1": 0, "week2": 0, "week3": 0, "week4": 0},
        "last_updated": None,
        "notes": []
    }

def save_progress(data):
    """Save progress to JSON file"""
    data["last_updated"] = datetime.now().isoformat()
    with open(PROGRESS_FILE, 'w') as f:
        json.dump(data, f, indent=2)

def mark_complete(task_type, task_name):
    """Mark a task as complete"""
    progress = load_progress()
    
    if task_type == "task":
        if task_name not in progress["completed_tasks"]:
            progress["completed_tasks"].append(task_name)
    elif task_type == "theory":
        if task_name not in progress["completed_theory"]:
            progress["completed_theory"].append(task_name)
    elif task_type == "project":
        if task_name not in progress["completed_projects"]:
            progress["completed_projects"].append(task_name)
    
    save_progress(progress)
    print(f"✅ Marked {task_type} '{task_name}' as complete")

def set_current(week, day):
    """Set current week and day"""
    progress = load_progress()
    progress["current_week"] = int(week)
    progress["current_day"] = int(day)
    save_progress(progress)
    print(f"📍 Set current position to Week {week}, Day {day}")

def add_note(note):
    """Add a note"""
    progress = load_progress()
    progress["notes"].append({
        "timestamp": datetime.now().isoformat(),
        "note": note
    })
    save_progress(progress)
    print(f"📝 Added note: {note}")

def show_status():
    """Show current status"""
    progress = load_progress()
    
    print("🎯 C++ Mastery Progress Status")
    print("=" * 40)
    print(f"Current Position: Week {progress['current_week']}, Day {progress['current_day']}")
    print(f"Last Updated: {progress.get('last_updated', 'Never')}")
    print()
    
    print("📊 Completion Summary:")
    print(f"  Tasks Completed: {len(progress['completed_tasks'])}")
    print(f"  Theory Completed: {len(progress['completed_theory'])}")
    print(f"  Projects Completed: {len(progress['completed_projects'])}")
    print()
    
    if progress["notes"]:
        print("📝 Recent Notes:")
        for note in progress["notes"][-3:]:  # Show last 3 notes
            print(f"  - {note['note']}")
        print()
    
    # Show next recommended action
    week = progress["current_week"]
    day = progress["current_day"]
    
    next_actions = {
        (1, 1): "Set up development environment and start Calculator project",
        (1, 2): "Complete Expression Parser and study control structures",
        (1, 3): "Begin OOP concepts and Shape Hierarchy project",
        (1, 4): "Master inheritance and polymorphism",
        (1, 5): "Implement Banking System with memory management",
        (1, 6): "Build Smart Pointer library and study RAII",
        (1, 7): "Complete Memory Pool and integration testing",
        (2, 1): "Master STL containers and build benchmark suite",
        # Add more as needed
    }
    
    next_action = next_actions.get((week, day), "Continue with current week's tasks")
    print(f"🎯 Next Recommended Action: {next_action}")

def generate_resume_guide():
    """Generate a resume guide based on current progress"""
    progress = load_progress()
    week = progress["current_week"]
    day = progress["current_day"]
    
    print("🚀 Quick Resume Guide")
    print("=" * 30)
    print(f"cd /home/eshdiar/cpp/cpp-mastery")
    print(f"cd week-{week}")
    print(f"cat README.md  # Review week overview")
    print(f"ls theory/     # Check theory files")
    print(f"ls projects/   # Check project files")
    print()
    print("To update progress after completing tasks:")
    print("python3 update_progress.py complete task 'task_name'")
    print("python3 update_progress.py complete theory 'theory_file'")
    print("python3 update_progress.py complete project 'project_name'")

def main():
    if len(sys.argv) < 2:
        show_status()
        return
    
    command = sys.argv[1]
    
    if command == "complete" and len(sys.argv) >= 4:
        task_type = sys.argv[2]
        task_name = sys.argv[3]
        mark_complete(task_type, task_name)
    
    elif command == "set" and len(sys.argv) >= 4:
        week = sys.argv[2]
        day = sys.argv[3]
        set_current(week, day)
    
    elif command == "note" and len(sys.argv) >= 3:
        note = " ".join(sys.argv[2:])
        add_note(note)
    
    elif command == "status":
        show_status()
    
    elif command == "resume":
        generate_resume_guide()
    
    else:
        print("Usage:")
        print("  python3 update_progress.py status")
        print("  python3 update_progress.py complete [task|theory|project] 'name'")
        print("  python3 update_progress.py set [week] [day]")
        print("  python3 update_progress.py note 'your note'")
        print("  python3 update_progress.py resume")

if __name__ == "__main__":
    main()
