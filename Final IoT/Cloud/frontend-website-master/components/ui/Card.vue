<script setup lang="ts">
const props = defineProps<{
    title: string
    value: string
    valueColor: string
    icon: Component
}>()

const textColor = computed(() => {
    return props.valueColor
})
</script>

<template>
    <div class="bg-white border border-gray-200 rounded-lg p-6 space-y-2">
        <div class="flex justify-between font-normal">
            <h2>
                {{ props.title }}
            </h2>
            <component
                :is="props.icon"
                class="h-5 w-5 text-gray-600"
            />
        </div>

        <h3 class="vcol font-bold text-2xl">
            {{ props.value }}
        </h3>
    </div>
</template>

<style scoped>
.vcol {
    color: v-bind(textColor)
}
</style>
