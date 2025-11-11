# AI Assistant Resume Context

## Program Overview
- **4-Week Intensive C++ Mastery Program**
- **Fast-paced, project-oriented learning**
- **Covers basics to advanced topics with data structures & algorithms**
- **Separate theory files from project READMEs**

## When User Returns
1. **Check Progress**: `python3 update_progress.py status`
2. **Load Current State**: Read `progress_state.json` for exact position
3. **Review Tracker**: Check `PROGRESS_TRACKER.md` for visual overview
4. **Navigate to Current**: Go to current week/day folder
5. **Provide Context**: Explain what's next based on progress

## Key Commands for AI to Use
```bash
# Check progress
cat /home/eshdiar/cpp/cpp-mastery/progress_state.json

# View tracker
cat /home/eshdiar/cpp/cpp-mastery/PROGRESS_TRACKER.md

# Get current week content
cat /home/eshdiar/cpp/cpp-mastery/week-X/README.md

# Check theory files
ls /home/eshdiar/cpp/cpp-mastery/week-X/theory/

# Update progress (after helping user complete tasks)
cd /home/eshdiar/cpp/cpp-mastery
python3 update_progress.py complete task "task_name"
```

## Resume Workflow
1. **Greet & Check**: "Welcome back! Let me check your C++ progress..."
2. **Status Report**: Show current week, day, completed items
3. **Context Refresh**: Briefly explain where they left off
4. **Next Steps**: Recommend immediate next actions
5. **Offer Help**: Ask how they want to proceed

## Progress Tracking Integration
- Always update progress when user completes tasks
- Use the Python script to maintain state
- Keep both human-readable and machine-readable formats
- Provide clear next steps based on current position

## User Phrases to Watch For
- "I'm back to continue C++ learning"
- "Check my progress" 
- "Where did I leave off"
- "Resume my C++ mastery"
- "Continue from where I stopped"

## Response Template
```
Welcome back to your C++ Mastery journey! 

📊 **Current Status**: Week X, Day Y
✅ **Completed**: [list recent completions]
🎯 **Next Up**: [specific next task/theory/project]

Would you like to:
1. Continue with [current task]
2. Review [relevant theory]
3. Get help with [current project]
4. Update your progress

Let me know how you'd like to proceed!
```
